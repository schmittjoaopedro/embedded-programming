'use strict';

var express = require('express'),
	router = express.Router(),
	fs = require('fs'),
	DAO;


router.post('/', function(req, res) {
	var dashboard = req.body;
	var components = req.body.components;
	DAO.User.findById(req.user.id, function(err, user) {
		DAO.Dashboard.save(user, dashboard, function(err, dashboard) {
			saveComponents(dashboard, components, 0, function(err) {
				if(!err)
					res.send("OK");
				else
					res.send(err);
			});
		});
	});
});

router.get('/', function(req, res) {
	res.sendfile('./views/dashboard/list.html');
});

router.get('/dashboards', function(req, res) {
	DAO.Dashboard.findAllDashboardsByUserId(req.user.id, function(err, data) {
		res.json(data || err);
	});
});


router.get('/dashboards/page/:dashboard', function(req, res) {
	req.session.dashboardCurrent = req.params['dashboard'];
	res.sendfile('./views/dashboard/index.html');
});

router.get('/header', function(req, res) {
	DAO.Dashboard.findById(req.session.dashboardCurrent, function(err, data) {
		if(err) res.error(err);
		else {
			var header = {
				userId: req.user.id,
				userName: req.user.name,
				dashboardId: req.session.dashboardCurrent,
				type: "Browser",
				isAuthenticated: true,
				dashboardName: data.name
			};
			res.json(header);
		}
	});
});

router.get('/dashboards/DashboardView', function(req, res) {
	DAO.Dashboard.findComponentsByDashboardId(req.session.dashboardCurrent, function(err, data) {
		if(err) {
			res.json(err);
		} else {
			var main = false;
			data.forEach(function(item) {
				if(item.componentType === 'DashboardView')
					main = item;
			});
			if(main)
					res.json(main);
		}
	});
});

router.get('/dashboards/All', function(req, res) {
	DAO.Dashboard.findComponentsByDashboardId(req.session.dashboardCurrent, function(err, data) {
		if(err) {
			res.json(err);
		} else {
			var main = [];
			data.forEach(function(item) {
				if(item.componentType !== 'DashboardView')
					main.push(item);
			});
			res.json(main);
		}
	});
});

router.delete('/delete/:dashboard', function(req, res) {
	DAO.Dashboard.remove(req.params['dashboard'], function(err, success) {
		if(err)
			res.json(err);
		else
			res.json(success);
	});
});

function saveComponents(dashboard, components, compCount, callback) {
	DAO.Component.save(dashboard, components[compCount], function(err, component) {
		if(!err) {
			if(compCount < components.length)
				saveComponents(dashboard, components, ++compCount, callback);
			else
				callback(false);
		} else {
			callback(err);
		}
	});
};

router.setDAO = function (db) {
	DAO = db;
};

module.exports = router;