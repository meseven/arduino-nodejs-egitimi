var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://127.0.0.1:1883');
// var client = mqtt.connect('mqtt://206.189.182.169:1883');

client.on('connect', async () => {
	console.log('connected');
});
