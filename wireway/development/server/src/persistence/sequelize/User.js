var crypto = require('crypto');

module.exports = function(sequelize, DataTypes) {
	var User = sequelize.define('User', {
		name: {
			type: DataTypes.STRING(60),
			allowNull: false
		},
		email: {
			type: DataTypes.STRING(200),
			allowNull: false,
			unique: true
		},
		password: {
			type: DataTypes.TEXT,
			allowNull: false,
			set: function(password) {
				this.setDataValue('password', crypto.createHash('sha1').update(password).digest('hex'));
			}
		},
	}, {
		classMethods: {
			associate: function(models) {
				User.belongsToMany(models.Dashboard, { through: 'DashboardUser' });
			}
		}
	});
	return User;
};