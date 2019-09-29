import React from 'react';
import {GoogleApiWrapper, Map, Marker} from 'google-maps-react';

export class MapContainer extends React.Component {
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
          onClick={this.onMapClicked}
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