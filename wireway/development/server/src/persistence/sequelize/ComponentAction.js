module.exports = function(sequelize, DataTypes) {
	var ComponentAction = sequelize.define('ComponentAction', {
		value: {
			type: DataTypes.STRING(50),
			allowNull: false
		}
	});
	return ComponentAction;
};