var map, marker;
function initMap() {
	map = new google.maps.Map(document.getElementById('map'), {
		center: { lat: -34.397, lng: 150.644 },
		zoom: 18,
	});

	marker = new google.maps.Marker({
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
			changeMap(message);
			break;
		default:
			break;
	}
});

function changeMap(message) {
	[lat, lng, altitude, speed, course] = message.toString().split(',');

	let position = { lat: parseFloat(lat), lng: parseFloat(lng) };
	marker.setPosition(position);
	map.setCenter(position);

	document.getElementById('km').innerHTML = speed;
	document.getElementById('msl').innerHTML = altitude;
}
