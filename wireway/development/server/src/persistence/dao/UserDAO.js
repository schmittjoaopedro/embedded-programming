'use strict'
/**
 * Especificação da Interface, callback receberá dois parâmetros:
 *		err = se der erro é retornado erro ou false se não será retornado true
 * 		data = objeto com status pode variar conforme a espec
 *
 * UserDAO
 *
 * 	-> save(user, callback) : callback(err, user)
 *
 * 	-> findById(id, callback) : callback(err, user)
 * 	-> findByLoginAndPassword(login, password) : callback(err, user)
 *	-> findByLogin(login) : callback(err, user)
 *
 *	-> remove(userId) : callback(err, true | false)
 * 	-> removeUser(user) : callback(err, true | false)
 *
 *	-> attachDashboardByUser(user, dashboard, callback) : callback(err, user)
 * 	-> disattachDashboard(user, dashboard, callback): callback(err, user)
 */
var crypto = require('crypto');


module.exports = function(db) {
	
	var _self = this;

	this.save = function(user, callback) {
		_self.findById(user.id, function(err, entity) {
			if(err) callback(err);
			if(entity) {
				entity
					.updateAttributes(user)
					.success(function(user) { callback(null, user); })
					.error(function(err) { callback(err); });
			} else {
				db.User
					.create(user)
					.success(function(user) { callback(null, user); })
					.error(function(err) { callback(err); });
			}
		});
	};

	this.findById = function(userId, callback) {
		if(userId !== undefined) {
			db.User.find({
				where: {
					id: userId
				}
			}).success(function(entity) {
				callback(null, entity);
			}).error(callback);
		} else {
			callback(null, null);
		}
	};

	this.findByLogin = function(login, callback) {
		db.User.find({
			where: {
				email: login
			}
		}).success(function(entity) {
			callback(null, entity);
		}).error(callback);
	};

	this.findByLoginAndPassword = function(login, password, callback) {
		db.User.find({
			where: {
				email: login,
				password: crypto.createHash('sha1').update(password).digest('hex')
			}
		}).success(function(entity) {
			callback(null, entity);
		}).error(callback);
	};

	this.remove = function(userId, callback) {
		_self.findById(userId, function(err, entity) {
			if(err) callback(err);
			if(entity) {
				entity
					.destroy()
					.success(function() { callback(null, true); })
					.error(function() { callback(null, false); });
			}
		});
	};

	this.removeUser = function(user, callback) {
		_self.removeUser(user.id, callback);
	};

	this.attachDashboardByUser = function(user, dashboard, callback) {
		_self.findById(user.id, function(err, user) {
			if(!dashboard.id) callback("Dashboard ID is Null");
			user.addDashboard(dashboard);
			callback(null, user);
		});
	};

	this.disattachDashboard = function(user, dashboard, callback) {
		_self.findById(user.id, function(err, user) {
			if(!dashboard.id) callback("Dashboard ID is Null");
			user.removeDashboard(dashboard);
			callback(null, user);
		});
	};

};