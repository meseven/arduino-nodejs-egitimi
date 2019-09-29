import React from 'react';
import {GoogleApiWrapper, Map, Marker} from 'google-maps-react';

import mqtt from 'mqtt';

export class MapContainer extends React.Component {
	state = {
		lat: -34.397, 
		lng: 150.644
	}

	updateMap(message){
		var [lat, lng, altitude, speed, course] = message.toString().split(',');

		this.setState({
			lat,
			lng
		})
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
	
	render(){
		const {lat,lng} = this.state;
		return(
			<div style={{ width: '100%', height: '100%' }}>
				<Map
          google={this.props.google}
          initialCenter={{
						lat, 
						lng
					}}
					center={{
						lat,
						lng
					}}
          zoom={18}
        >
					<Marker
						icon= {{
							path: window.google.maps.SymbolPath.FORWARD_CLOSED_ARROW,
							fillColor: 'red',
							fillOpacity: 0.9,
							strokeWeight: 6,
							scale: 8,
							rotation: 0,
						}}
						position={{ lat, lng }}
					/>
				</Map>
			</div>
		)
	}
}

export default GoogleApiWrapper({
  apiKey: ("AIzaSyAEAVPs6jLAgdIGk58JSMG5GO0jHICT40Q")
})(MapContainer)