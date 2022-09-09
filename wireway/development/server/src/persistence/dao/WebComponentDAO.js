/**
 * Especificação da Interface, callback receberá dois parâmetros:
 *		err = se der erro é retornado erro ou false se não será retornado true
 * 		data = objeto com status pode variar conforme a espec
 *
 * WebComponentDAO
 *
 * 	-> save(webComponent, callback) : callback(err, webComponent)
 *
 * 	-> findById(webComponentId, callback) : callback(err, webComponent)
 *	-> findByComponentId(componentId, callback) : callback(err, webComponent)
 *	-> findByWebTemplateId(webTemplateId, callback) : callback(err, [webComponent])
 *	-> findAllByDashboardId(dashboardId, callback) : callback(err, [webComponent])
 *
 *	-> remove(webComponentId) : callback(err, true | false)
 * 	-> removeWebComponent(webComponent) : callback(err, true | false)
 *
 */

module.exports = function(db) {
	
};