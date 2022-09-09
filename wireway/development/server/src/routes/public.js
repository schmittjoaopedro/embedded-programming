'use strict';

var express = require('express'),
	router = express.Router(),
	fs = require('fs'),
	DAO;

router.get('/', function (req, res, next) {
 	res.render('views/login');
});

router.get('/header', function (req, res, next) {
 	res.render('views/header');
});

router.get('/register', function (req, res, next) {
	res.sendfile('./views/user/register.html')
});

router.post('/register/user', function(req, res) {
	DAO.User.save(req.body, function(err, user) {
		if(err || !user.id) {
			res.status(500).send(err);
		} else {
			res.send(user);
		}
	});
});

router.setDAO = function (db) {
	DAO = db;
};

module.exports = router;