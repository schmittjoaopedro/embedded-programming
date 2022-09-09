module.exports = function(sequelize, DataTypes) {
	var Config = sequelize.define('Config', {
		key: {
			type: DataTypes.STRING(50),
			allowNull: false
		},
		value: {
			type: DataTypes.STRING(500),
			allowNull: false
		}
	});
	return Config;
};