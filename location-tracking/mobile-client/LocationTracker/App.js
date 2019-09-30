import React, { Component } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import MapView, { Marker } from 'react-native-maps';

import mqtt from 'mqtt/dist/mqtt';

export default class App extends Component {
	state = {
		lat: -34.397,
		lng: 150.644,
		altitude: 0,
		speed: 0,
		course: 0,
	};

	updateMap(message) {
		var [lat, lng, altitude, speed, course] = message.toString().split(',');

		this.setState({
			lat: parseFloat(lat),
			lng: parseFloat(lng),
			altitude,
			speed,
			course,
		});
	}

	componentDidMount() {
		var client = mqtt.connect('ws://157.230.113.66:3000');

		client.subscribe('LOCATION');

		client.on('connect', function() {
			console.log('connected!');
		});

		client.on('message', (topic, message) => {
			console.log(topic, ' : ', message.toString());
			switch (topic) {
				case 'LOCATION':
					this.updateMap(message);
					break;
			}
		});
	}

	render() {
		const { lat, lng, altitude, speed, course } = this.state;

		return (
			<View style={styles.container}>
				<MapView
					style={{ flex: 1 }}
					initialRegion={{
						latitude: lat,
						longitude: lng,
						latitudeDelta: 0.006,
						longitudeDelta: 0.0002,
					}}
					region={{
						latitude: lat,
						longitude: lng,
						latitudeDelta: 0.006,
						longitudeDelta: 0.0002,
					}}
				>
					<Marker
						coordinate={{
							latitude: lat,
							longitude: lng,
						}}
						image={require('./assets/arrow.png')}
						style={{
							transform: [
								{
									rotate: course + 'deg',
								},
							],
						}}
					/>
				</MapView>

				<View style={styles.info}>
					<Text style={styles.value}>
						{speed}
						<Text style={styles.text}> km/h</Text>
					</Text>
					<Text style={[styles.value, styles.msl]}>
						{altitude}
						<Text style={styles.text}> msl</Text>
					</Text>
				</View>
			</View>
		);
	}
}

const styles = StyleSheet.create({
	container: {
		flex: 1,
	},
	info: {
		backgroundColor: '#e1e1e1',
		position: 'absolute',
		padding: 25,
		opacity: 0.5,
		left: 0,
		bottom: 100,
	},
	value: {
		fontSize: 30,
	},
	msl: {
		fontSize: 18,
	},
	text: {
		fontSize: 14,
	},
});
