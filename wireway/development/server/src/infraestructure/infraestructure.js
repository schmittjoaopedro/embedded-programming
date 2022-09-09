var socket = require('socket.io'),
	expressSocketSession = require("express-socket.io-session"),
	fs = require('fs');

/**
 * @param express
 * @param httpServer
 * @param session
 *
 * PACOTES COMUNICACAO EXECUCAO
 *
 * web -> server | server -> client | client -> server | server -> web
 * 	packet: {
 * 		header: {
 * 			userId,
 * 			userName,
 * 			userPassword,
 * 			dashboardId,
 * 			type: 'Browser'
 * 		},
 * 		body: {
 * 			script: {
 * 				content,
 * 				file
 * 			},
 * 			components: [{
 * 				id,
 * 				idName,
 * 				value
 * 			}]
 * 		}
 * 	}
 *
 * Classe para gerenciar comunicação dos Web Clients com os Clients Clouds,
 * usa sessão HTTP para validar usuários WS
 */

function infraestructureSocket(express, httpServer, session, DAO) {

	var io = socket.listen(httpServer.listen(express.get('port')));

	//Validação de sessão, se não válido não continua
	//para pegar sessão no socket basta: console.info(socket.handshake.session);
	io.use(expressSocketSession(session));
	io.use(function(socket, next) {
		if (socket.request.headers.cookie) return next();
		next(new Error('Authentication error'));
	});


	//Em obras...
	io.on('connection', function(socket) {

		socket.on('client setup', function(data) {
			socket.join(data.header.dashboardId + '');


			DAO.Dashboard.findById(data.header.dashboardId, function(err, dash) {
				if(dash && dash.currentScript) {
					fs.readFile('./scripts/' + data.header.dashboardId + '/' + dash.currentScript, 'utf8', function(err, scriptData) {
						var pkg = {
							header: data.header,
							body: {
								script: {
									content: scriptData,
									file: dash.currentScript
								}
							}
						};
						
						DAO.Dashboard.findComponentsByDashboardId(data.header.dashboardId, function(err, components) {
							pkg.body.components = components;
							io.to(data.header.dashboardId + '').emit('client setup', pkg);
						});
					});
				}
			});
			
		});

		socket.on('upload script', function(data) {
			fs.readFile('./scripts/joao/home/home.js', 'utf8', function(err, scriptData) {
				pkg.body.script.content = scriptData;
				pkg.body.script.file = './scripts/joao/home/home.js';
				io.to(data.header.dashboardId + '').emit('client setup', pkg);
			});
		});

		socket.on('browser_join', function(data) {
			socket.join(data.header.dashboardId + '');
		})

		socket.on('cloud_data', function(data) {
			io.to(data.header.dashboardId + '').emit('browser_data', data);
		});

		socket.on('browser_data', function(data) {
			io.to(data.header.dashboardId + '').emit('cloud_data', data);
		});

	});


}

module.exports = infraestructureSocket;