module.exports = function(sequelize, DataTypes) {
	var Dashboard = sequelize.define('Dashboard', {
		name: {
			type: DataTypes.STRING(60),
			allowNull: false
		},
		description: {
			type: DataTypes.STRING(300)
		},
		latitude: {
			type: DataTypes.FLOAT
		},
		longitude: {
			type: DataTypes.FLOAT
		},
		currentScript: {
			type: DataTypes.STRING(300)
		}
	}, {
		classMethods: {
			associate: function(models) {
				Dashboard.belongsToMany(models.User, { through: 'DashboardUser' });
				Dashboard.hasMany(models.Component, { onDelete: 'CASCADE' });
			}
		}
	});
	return Dashboard;
}