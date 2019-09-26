var client = mqtt.connect('ws://157.230.113.66:3000');

client.subscribe('LOCATION');

client.on('connect', function() {
	console.log('connected!');
});

client.on('message', function(topic, message) {
	console.log(topic, ' : ', message.toString());
	switch (topic) {
		case 'LOCATION':
			[lat, lng, altitude, speed, course] = message.toString().split(',');

			break;
		default:
			break;
	}
});

var map;
function initMap() {
	map = new google.maps.Map(document.getElementById('map'), {
		center: { lat: -34.397, lng: 150.644 },
		zoom: 8,
	});
}
