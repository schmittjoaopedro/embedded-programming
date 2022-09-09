/**
 * Especificação da Interface, callback receberá dois parâmetros:
 *		err = se der erro é retornado erro ou false se não será retornado true
 * 		data = objeto com status pode variar conforme a espec
 *
 * ComponentDAO
 *
 * 	-> save(dashboard, component, callback) : callback(err, component)
 *	-> saveComponentAction(component, action, callback) : callback(err, action)
 *	-> saveComponentRead(component, read, callback) : callback(err, read)
 *
 *	-> findById(componentId, callback) : callback(err, component)
 * 	-> findDashboardByComponentId(componentId, callback) : callback(err, dashboard)
 *	-> findComponentsByIdName(idName, callback) : callback(err, [components])
 *	-> findWebComponentByComponentId(componentId, callback) : callback(err, webComponent)
 *
 *	-> remove(componentId, callback) : callback(err, true | false)
 *	-> removeComponent(component, callback) : callback(err, true | false)
 */

module.exports = function(db) {

	var _self = this;

	this.save = function(dashboard, component, callback) {
		_self.findById(component.id, function(err, entity) {
			if(err) callback(err);
			if(entity) {
				entity
					.updateAttributes(component)
					.success(function(componentEntity) {
						__saveConfigs(componentEntity, __transformConfig(component.config), 0, function() {
							__findWebTemplateById(component.webTemplate.id, function(err, webTemplate) {
								webTemplate.addComponent(componentEntity)
								.done(function() {
									dashboard.addComponent([componentEntity])
									.done(function() {
										callback(null, componentEntity);
									})
									.error(function() {
										callback(err);
									});
								})
								.error(function() {
									callback(err);
								});
							});
						});
					})
					.error(function(err) { callback(err); });
			} else {
				db.Component
					.create(component)
					.success(function(componentEntity) {
						__saveConfigs(componentEntity, __transformConfig(component.config), 0, function() {
							__findWebTemplateById(component.webTemplate.id, function(err, webTemplate) {
								webTemplate.addComponent(componentEntity)
								.done(function() {
									dashboard.addComponent([componentEntity])
									.done(function() {
										callback(null, componentEntity);
									})
									.error(function() {
										callback(err);
									});
								})
								.error(function() {
									callback(err);
								});
							});
						});
					})
					.error(function(err) { callback(err); });
			}
		});
	};

	this.findById = function(componentId, callback) {
		if(componentId !== undefined) {
			db.Component.find({
				where: {
					id: componentId
				}
			}).success(function(entity) {
				callback(null, entity);
			}).error(callback);
		} else {
			callback(null, null);
		}
	};

	function __findWebTemplateById (webTemplateId, callback) {
		if(webTemplateId !== undefined) {
			db.WebTemplate.find({
				where: {
					id: webTemplateId
				}
			}).success(function(entity) {
				callback(null, entity);
			}).error(callback);
		} else {
			callback(null, null);
		}
	};

	function __saveConfigs(componentEntity, configs, idx, callback) {
		if(idx < configs.length) {
			db.Config
			.build(configs[idx])
			.save()
			.success(function(config) {
				componentEntity.addConfig(config)
				.success(function(configComponent) {
					__saveConfigs(componentEntity, configs, ++idx, callback);
				})
				.error(function(err) { callback(err); });
			})
			.error(function(err) { callback(err); });
		} else {
			callback();
		}
	};

	function __transformConfig(configs) {
		var configsTransformed = [];
		for(var prop in configs) {
			configsTransformed.push({
				key: prop,
				value: configs[prop]
			});
		}
		return configsTransformed;
	};

};