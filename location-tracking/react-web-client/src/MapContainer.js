import React from 'react';
import {GoogleApiWrapper, Map, Marker} from 'google-maps-react';

import mqtt from 'mqtt';

export class MapContainer extends React.Component {
	componentDidMount() {
		var client = mqtt.connect('ws://157.230.113.66:3000');

		client.subscribe('LOCATION');

		client.on('connect', function() {
			console.log('connected!');
		});

		client.on('message', function(topic, message) {
			console.log(topic, ' : ', message.toString());
			switch (topic) {
				case 'LOCATION':
					// updateMap(message);
					break;
				default:
					break;
			}
		});
	}
	
	render(){
		return(
			<div style={{ width: '100%', height: '100%' }}>
				<Map
          google={this.props.google}
          initialCenter={{
						lat: 47.444, 
						lng: -122.176
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
						position={{ lat: 47.444, lng: -122.176 }}
					/>
				</Map>
			</div>
		)
	}
}

export default GoogleApiWrapper({
  apiKey: ("AIzaSyAEAVPs6jLAgdIGk58JSMG5GO0jHICT40Q")
})(MapContainer)