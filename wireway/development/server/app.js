'use strict';

/**
 * Este arquivo é responsável por iniciar a inicialização de todos os módulos da aplicação abaixo:
 *  -> express (camada REST)
 *  -> passport (camada de segurança HTTP - WS)
 *  -> infraestructure (camada de aplicação WS, core a aplicação)
 *  -> DAO (persistencia para base de dados)
 */

var express = require('express'),
    path = require('path'),
    cookieParser = require('cookie-parser'),
    bodyParser = require('body-parser'),
    security = require('./src/configs/passport'),
    swig = require('swig'),
    app = express(),
    infraestructure = require('./src/infraestructure/infraestructure'),
    persistence = require('./src/persistence/DAO'),
    DAO = new persistence();

var session = require('express-session')({
  secret: 'wireway',
  resave: false,
  saveUninitialized: false
});

app.engine('html', swig.renderFile);
app.set('view engine', 'html');
app.set('views', __dirname);
app.set('view cache', false);
swig.setDefaults({ cache: false });
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(session);
app.use(express.static(path.join(__dirname, 'public')));

security.initialize(app, DAO);

var routerPublic = require('./src/routes/public'),
    routerHome = require('./src/routes/home'),
    routerTemplates = require('./src/routes/template'),
    routerAdmin = require('./src/routes/admin'),
    routerDashboard = require('./src/routes/dashboard.js'),
    routerScript = require('./src/routes/script.js');

app.use('/', routerPublic);
app.use('/home', routerHome);
app.use('/admin', routerAdmin);
app.use('/template', routerTemplates);
app.use('/dashboard', routerDashboard);
app.use('/script', routerScript);

routerPublic.setDAO(DAO);
routerTemplates.setDAO(DAO);
routerDashboard.setDAO(DAO);
routerHome.setDAO(DAO);
routerScript.setDAO(DAO);

/**
 * Inicaliza a aplicação seguindo um fluxo de callbacks
 *  -> Primeiro carrega a base de dados
 *     -> Depois carrega o servidor HTTP
 *        -> Com instancia do servidor HTTP inicia o Socket IO
 */
 console.info("Starting...");
app.startServer = function(httpServer) {
	DAO.start(function() {
		app.infraestructure = new infraestructure(app, httpServer, session, DAO);
        console.info("===================================================");
	});
};

module.exports = app;