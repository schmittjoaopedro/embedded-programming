'use strict';

/**
 * Configura validação de sessão para usuários através de um filtro
 * configurado nas rotas, se não estiver autenticado redireciona para
 * pagina de autenticação aonde válida as credencias com as do banco,
 * a estratégia é local porque impacta na validação de usuário WS.
 */

var passport = require('passport'),
	LocalStrategy = require('passport-local').Strategy,
	DAO;

function wirewaySecurity() { };

//Validação da sessção do usuário
function validAuthentication(req, res, next){
	if(req.isAuthenticated()) {
		next();
	}else{
		res.redirect('/');
	}
};

wirewaySecurity.prototype.validAuthentication = function(req, res, next) {
	validAuthentication(req, res, next);
};

wirewaySecurity.prototype.findUser = function(username, password, done) {
	DAO.User.findByLoginAndPassword(username, password, function(err, user) {
		if(err) {
			return done(err, false);
		} else {
			if(user) {
				return done(null, user);
			} else {
				return done(null, false, { message: 'Invalid User' });
			}
		}
	});
};

wirewaySecurity.prototype.initialize = function(express, db) {

	DAO = db;
	this.app = express;
	this.app.use(passport.initialize());
	this.app.use(passport.session());
	//Método de autenticação com a base de dados
	passport.use(new LocalStrategy(this.findUser));

	//Adiciona usuário a requisição HTTP
	passport.serializeUser(function(user, done) {
		done(null, user);
	});

	//Recupera usuário com base no ID da requisição
	passport.deserializeUser(function(user, done) {
		done(null, user);
	});

	//Filtro de autenticação
	this.app.post('/login', passport.authenticate('local', {
		successRedirect: '/home',
		failureRedirect: '/'
	}));

	//Logout
	this.app.get('/logout', function(req, res){
		req.logout();
		res.redirect('/');
	});

	//Todas rotas que precisam de autenticação
	this.app.use('/home', validAuthentication);
	this.app.use('/admin', validAuthentication);
	this.app.use('/template', validAuthentication);
	this.app.use('/dashboard', validAuthentication);
	this.app.use('/script', validAuthentication);
};

module.exports = new wirewaySecurity();