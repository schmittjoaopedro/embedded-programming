(function(__manager) {

	var _local = wireway.manager = {

		sendComponent: function(comp) {
			if(_local.isConnected) {
				var packet = {
					header: _local.header,
					body: {
						components: [comp]
					}
				};
				_local.socket.emit('browser_data', packet);
			}
		},

		start: function() {
			$.get('/dashboard/header').done(function(data) {
				_local.header = data;
			  socket = io.connect('http://localhost:3000');
			  socket.emit('browser_join', { header: _local.header });
			  _local.isConnected = true;
			  socket.on('browser_data', function(data) {
			  	var components = data.body.components;
			  	for(var item in components) {
			  		wireway.getCmp(components[item].idName).setPacket(components[item]);
			  	}
			  });
			  _local.socket = socket;
			});
		}

	};

}(wireway));