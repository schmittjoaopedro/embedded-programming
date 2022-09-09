var db = require('./sequelize/sequelize.js');

/**
 * Classe mestre que disponibilizará uma interface que será usada, escondendo
 * a implementação da base de dados utilizada das camadas de serviço, para esse
 * os modelos que serão persistidos configurados via sequelize estão na pasta sequelize,
 * o arquivo sequelize.js inicia a instanciação de todos os models e inicia a conexão com o banco.
 *
 * Cada arquivo possui a descrição da interface disponibilizada
 */

var userDao = require('./dao/UserDAO');
var componentDao = require('./dao/ComponentDAO');
var dashboardDao = require('./dao/DashboardDAO');
var webComponentDao = require('./dao/WebComponentDAO');
var webTemplateDao = require('./dao/WebTemplateDAO');

function DAO() {

	//Iniciliza aplicação e chama callback para inicar servidor
	this.start = function(callback) {
		db.sequelize.sync({ force: false }).done(function(err) {
			if(!err) callback();
			else throw err;
		});
	};

	//Instancia Implementações passando Sequelize
	this.User = new userDao(db);
	this.Component = new componentDao(db);
	this.Dashboard = new dashboardDao(db);
	this.WebComponent = new webComponentDao(db);
	this.WebTemplate = new webTemplateDao(db);

};

module.exports = DAO;