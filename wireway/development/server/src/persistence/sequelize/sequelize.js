/**
 * Configura conexão com a base de dados, usando MySQL, e carrega todos
 * os modelos da base, gerando o banco de force = true, depois retorna um
 * objeto "db"
 */

var Sequelize = require('sequelize'),
	path = require('path'),
    lodash = require('lodash'),
	sequelize = new Sequelize('wireway', 'root', 'system', {
		dialect: 'mysql'
	}),
	db = {},
	persistentsModels = [
		'User',
		'Dashboard',
		'Component',
		'ComponentAction',
		'ComponentRead',
		'WebTemplate',
		'Config'
	];


for(var i = 0; i < persistentsModels.length; i++)
	db[persistentsModels[i]] = sequelize.import(path.join(__dirname, persistentsModels[i]));

for(var i = 0; i < persistentsModels.length; i++) {
	if (db[persistentsModels[i]].associate != undefined) {
	    db[persistentsModels[i]].associate(db)
	}
}

module.exports = lodash.extend({
    sequelize: sequelize,
    Sequelize: Sequelize
}, db)