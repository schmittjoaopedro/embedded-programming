'use strict';

var app = require('./app'),
    http = require('http'),
    port = (process.env.PORT || 3000),
    server = http.createServer(app);

app.set('port', port);
server.on('error', onError);
server.on('listening', onSuccess);

app.startServer(server);

function onSuccess() {
  console.log('Port ' + port);
};

function onError(error) {
  console.log('Error: ' + error);
};