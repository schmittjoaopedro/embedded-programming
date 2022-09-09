/**
 * Especificação da Interface, callback receberá dois parâmetros:
 *		err = se der erro é retornado erro ou false se não será retornado true
 * 		data = objeto com status pode variar conforme a espec
 *
 * WebTemplateDAO
 *
 * 	-> save(webTemplate, callback) : callback(err, webTemplate)
 *
 *	-> findById(webTemplateId, callback) : callback(err, webTemplate)
 *	-> findByComponentType(componentType, callback) : callback(err, [webTemplates])
 *	-> findByComponentId(webComponentId, callback) : callback(err, webTemplate)
 *	-> findThatContainsJS(jsQuery, callback) : callback(err, [webTemplates])
 *	-> findThatContainsCSS(cssQuery, callback) : callback(err, [webTemplates])
 *	-> findThatContainsHTML(htmlQuery, callback) : callback(err, [webTemplates])
 *
 *	-> remove(webTemplateId, callback) : callback(err, true | false)
 *	-> removeWebTemplate(webTemplate, callback) : callback(err, true | false)
 *
 */

module.exports = function(db) {

	var _self = this;

	this.save = function(webTemplate, callback) {
		_self.findById(webTemplate.id, function(err, entity) {
			if(err) callback(err);
			if(entity) {
				entity
					.updateAttributes(webTemplate)
					.success(function(webTemplate) { callback(null, webTemplate); })
					.error(function(err) { callback(err); });
			} else {
				db.WebTemplate
					.create(webTemplate)
					.success(function(webTemplate) { callback(null, webTemplate); })
					.error(function(err) { callback(err); });
			}
		});
	};

	this.findById = function(webTemplateId, callback) {
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

	this.findByComponentType = function (componentType, callback) {
		if(componentType != undefined) {
			if(!Array.isArray(componentType)) componentType = [componentType];
			db.WebTemplate.findAll({
				where: {
					componentType: {
						in: componentType
					}
				}
			}).success(function(entity) {
				callback(null, entity);
			}).error(callback);
		} else {
			callback(null, null);
		}
	};

};