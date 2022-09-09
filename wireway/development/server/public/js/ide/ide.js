var logged = false, socket;

/** PACOTE PARA SCRIPTS
 * 
 * eg.
 * 
 * packet = {
 * 		header: {
 * 			userId: 1,
 * 			userName: 'joao',
 * 			userPassword: 1,
 * 			dashboardId: 1,
 * 			type: 'Browser'
 * 		},
 * 		body: {
 * 			script: {
 * 				content: data,
 * 				file: 'home.js'
 * 			}
 * 		}
 * }
 * 
 */

var packet = {
		header: {
			userId: 1,
			userName: 'joao',
			userPassword: 'asd123',
			dashboardId: 2,
			type: 'Browser'
		}		
	};

$('#save').click(function() {

	packet.body = {
		script: { 
			content: editor.getValue(),
			script: 'home.js'
		}
	};
	
	$.ajax({
		url: '/admin/script',
		type: 'post',
		data: JSON.stringify(packet),
		contentType: 'application/json'
	});

});

$('#upload').click(function() {
	
	if(!logged) {
		logged = true;

		socket = io.connect('http://localhost:3000');

		socket.on('connect', function() {
			socket.emit('authentication', { username: 'joao', password: 'asd123' });
	  	});
		
	  	socket.on('reconnect', function() {
	  		//socket.emit('authentication', packet);
	  	});

	  	socket.on('authenticated', function() {
	  		console.info('Authenticated');
	  	});
	  	
		/*socket.on('web data', function(data) {
			$('#log').prepend(JSON.stringify(data) + '<br />');
		});*/
	}
	
	if(socket.connected) {
		packet.body = {
			script: {
				content: editor.getValue(),
				file: 'home.js'
			}	
		};
		socket.emit('upload script', packet);
	}
	
});

$('#refresh').click(function() {
	$.get('/admin/script').done(function(data) {
		editor.setValue(data);
	});
});

$(document).on('ready', function () {
	
});
