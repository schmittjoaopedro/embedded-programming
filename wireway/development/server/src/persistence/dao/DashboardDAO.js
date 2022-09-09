/**
 * Especificação da Interface, callback receberá dois parâmetros:
 *		err = se der erro é retornado erro ou false se não será retornado true
 * 		data = objeto com status pode variar conforme a espec
 *
 * DashboardDAO
 *
 * 	-> save(user, dashboard, callback) : callback(err, dashboard)
 *
 * 	-> findById(id, callback) : callback(err, dashboard)
 *	-> findAllDashboardsByUserId(userId, callback) : callback(err, [dashboards])
 * 	-> findDashboardById(dashboardId, callback) : callback(err, dashboard)
 *	-> findComponentsByDashboardId(dashboardId, callback) : callback(err, [components])
 * 	-> findWebComponentsByDashboardId(dashboardId, callback) : callback(err, [webComponents])
 *
 * 	-> remove(dashboardId, callback) : callback(err, true | false)
 *	-> removeDashboard(dashboard, callback) : callback(err, true | false)
 *
 *	-> attachUser(user, dashboard, callback) : callback(err, dashboard)
 *	-> disattachUser(user, dashboard, callback) : callback(err, dashboard)
 *
 *	-> attachComponent(component, dashboard, callback) : callback(err, dashboard)
 *	-> disattachComponent(component, dashboard, callback) : callback(err, dashboard)
 *
 *	-> attachWebComponent(webComponent, dashboard, callback) : callback(err, dashboard)
 *	-> disattachWebComponent(webComponent, dashboard, callback) : callback(err, dashboard)
 */

module.exports = function(db) {

	var _self = this;

	this.save = function(user, dashboard, callback) {
		_self.findById(dashboard.id, function(err, entity) {
			if(err) callback(err);
			if(entity) {
				entity
					.updateAttributes(dashboard)
					.success(function(dashboard) {
						dashboard.addUser([user]).done(function() {
							callback(null, dashboard);
						});
					})
					.error(function(err) { callback(err); });
			} else {
				db.Dashboard
					.create(dashboard)
					.success(function(dashboard) {
						dashboard.addUser([user]).done(function() {
							callback(null, dashboard);
						});
					})
					.error(function(err) { callback(err); });
			}
		});
	};

	this.findById = function(dashboardId, callback) {
		if(dashboardId !== undefined) {
			db.Dashboard.find({
				where: {
					id: dashboardId
				}
			}).success(function(entity) {
				callback(null, entity);
			}).error(callback);
		} else {
			callback(null, null);
		}
	};

	this.findAllDashboardsByUserId = function (userId, callback) {
		if(userId) {
			db.User.find({
				where: {
					id: userId
				},
				include: [db.Dashboard]
			}).success(function(user) {
				callback(null, user.toJSON().Dashboards);
			}).error(function(err) { callback(err); });
		} else {
			callback("UserId is null", null);
		}
	};

	this.findComponentsByDashboardId = function(dashboardId, callback) {
		if(dashboardId) {
			db.Dashboard.find({
				where: {
					id: dashboardId
				},
				include: [db.Component]
			}).success(function(dashboard) {

				var components = [];

				dashboard.getComponents().success(function(entitys) {
					entitys.forEach(function(item) {
						components.push(item.toJSON());
					});
					loadConfigsAndWebTemplates(entitys, components, 0, function(data) {
						callback(null, data);
					});
				});

			}).error(function(err) { callback(err); });

		} else {
			callback("dashboardId is null", null);
		}
	};


	this.remove = function (dashboardId, callback) {
		_self.findById(dashboardId, function(err, entity) {
			if(err) {
				callback(err);
			} else {
				if(!entity) {
					callback(null, false);
				} else {
					entity.destroy({ force: true }).then(function() {
						callback(null, true);
					})
				}
			}
		});
	}

	function loadConfigsAndWebTemplates(entitys, components, idx, callback) {
		if(idx < components.length) {
			entitys[idx].getWebTemplate().success(function(webTemplate) {
				components[idx].webTemplate = webTemplate.toJSON();
				entitys[idx].getConfigs().success(function(configs) {
					components[idx].config = {};
					if(configs) {
						configs.forEach(function(config) {
							var temp = config.toJSON();
							components[idx].config[temp.key] = temp.value;
						});
					}
					loadConfigsAndWebTemplates(entitys, components, ++idx, callback);
				});
			});
		} else {
			callback(components);
		}
	}


};


