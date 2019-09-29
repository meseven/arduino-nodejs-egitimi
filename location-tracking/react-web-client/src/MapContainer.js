import React from 'react';
import {GoogleApiWrapper, Map} from 'google-maps-react';

export class MapContainer extends React.Component {
	render(){
		return(
			<div style={{ width: '100%', height: '100%' }}>
				<Map
          google={this.props.google}
          initialCenter={{
            lat: 40.854885,
            lng: -88.081807
          }}
          zoom={12}
          onClick={this.onMapClicked}
        />
			</div>
		)
	}
}

export default GoogleApiWrapper({
  apiKey: ("AIzaSyAEAVPs6jLAgdIGk58JSMG5GO0jHICT40Q")
})(MapContainer)