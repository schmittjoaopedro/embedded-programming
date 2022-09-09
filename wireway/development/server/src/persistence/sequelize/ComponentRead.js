module.exports = function(sequelize, DataTypes) {
	var ComponentRead = sequelize.define('ComponentRead', {
		value: {
			type: DataTypes.STRING(50),
			allowNull: false
		}
	});
	return ComponentRead;
};