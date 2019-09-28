var map, marker;
function initMap() {
	map = new google.maps.Map(document.getElementById('map'), {
		center: { lat: -34.397, lng: 150.644 },
		zoom: 18,
	});

	var symbol = {
		// url: 'car.png',
		path: google.maps.SymbolPath.FORWARD_CLOSED_ARROW,
		fillColor: 'red',
		fillOpacity: 0.9,
		strokeWeight: 6,
		scale: 8,
		rotation: 0,
	};

	marker = new google.maps.Marker({
		icon: symbol,
		map,
	});
}

// mqtt
var client = mqtt.connect('ws://157.230.113.66:3000');

client.subscribe('LOCATION');

client.on('connect', function() {
	console.log('connected!');
});

client.on('message', function(topic, message) {
	console.log(topic, ' : ', message.toString());
	switch (topic) {
		case 'LOCATION':
			updateMap(message);
			break;
		default:
			break;
	}
});

function updateMap(message) {
	[lat, lng, altitude, speed, course] = message.toString().split(',');

	let position = { lat: parseFloat(lat), lng: parseFloat(lng) };
	marker.setPosition(position);
	marker.setIcon({ ...marker.getIcon(), rotation: parseInt(course) });
	map.setCenter(position);

	document.getElementById('km').innerHTML = speed;
	document.getElementById('msl').innerHTML = altitude;
}
