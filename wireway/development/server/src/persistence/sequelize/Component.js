module.exports = function(sequelize, DataTypes) {
	var Component = sequelize.define('Component', {
		idName: {
			type: DataTypes.STRING(60),
			allowNull: false
		},
		description: {
			type: DataTypes.STRING(300)
		},
		dataType: {
			type: DataTypes.ENUM('Number', 'String', 'Boolean', 'Array'),
			defaultValue: 'String'
		},
		componentType: {
			type: DataTypes.ENUM('Numeric', 'Digital', 'PWM', 'Analog',' Chart', 'Console', 'DashboardView'),
			allowNull: false
		},
		sendWhenChange: {
			type: DataTypes.BOOLEAN,
			defaultValue: true
		},
		persistData: {
			type: DataTypes.BOOLEAN,
			defaultValue: false
		}
	}, {
		classMethods: {
			associate: function(models) {
				Component.hasMany(models.ComponentAction, { onDelete: 'CASCADE' });
				Component.hasMany(models.ComponentRead, { onDelete: 'CASCADE' });
				Component.hasMany(models.Config, { onDelete: 'CASCADE' });
				Component.belongsTo(models.WebTemplate);
			}
		}
	});
	return Component;
};