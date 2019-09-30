import React, { Component } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import MapView, { Marker } from 'react-native-maps';

export default class App extends Component {
	render() {
		return (
			<View style={styles.container}>
				<MapView
					style={{ flex: 1 }}
					initialRegion={{
						latitude: 37.78825,
						longitude: -122.4324,
						latitudeDelta: 0.006,
						longitudeDelta: 0.0002,
					}}
				>
					<Marker
						coordinate={{
							latitude: 37.78825,
							longitude: -122.4324,
						}}
						image={require('./assets/arrow.png')}
					/>
				</MapView>
			</View>
		);
	}
}

const styles = StyleSheet.create({
	container: {
		flex: 1,
	},
});
