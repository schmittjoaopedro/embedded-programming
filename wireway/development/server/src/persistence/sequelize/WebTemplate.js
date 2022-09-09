module.exports = function(sequelize, DataTypes) {
	var WebTemplate = sequelize.define('WebTemplate', {
		componentType: {
			type: DataTypes.ENUM('Numeric','Digital', 'PWM', 'Analog',' Chart', 'Console', 'DashboardView'),
			allowNull: false
		},
		description: {
			type: DataTypes.STRING(100)
		},
		html: {
			type: DataTypes.STRING(4000),
			allowNull: false
		},
		js: {
			type: DataTypes.STRING(4000)
		},
		css: {
			type: DataTypes.STRING(4000)
		},
		configHtml: {
			type: DataTypes.STRING(4000)
		}
	}, {
		classMethods: {
			associate: function(models) {
				WebTemplate.hasMany(models.Component);
			}
		}
	});
	return WebTemplate;
};