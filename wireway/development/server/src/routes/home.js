'use strict';

var express = require('express'),
	router = express.Router(),
	DAO;

router.get('/', function (req, res, next) {
	res.render('views/home', {
		title: 'Home'
	});
});

router.get('/user/dashboards', function(req, res) {

	DAO.Dashboard.findAllDashboardsByUserId(req.user.id, function(err, data) {
		if(err)
			res.send("Error")
		else
			res.json(data);
	});

});

router.setDAO = function (db) {
	DAO = db;
};

module.exports = router;