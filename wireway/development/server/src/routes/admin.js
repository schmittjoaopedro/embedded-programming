'use strict';

var express = require('express'),
	router = express.Router(),
	fs = require('fs');


router.get('/', function (req, res, next) {
	res.render('views/home', {
		title: 'Scripts'
	});
});


router.get('/ide', function (req, res, next) {
	res.render('views/ide', {
		title: 'Scripts'
	});
});

router.get('/script', function(req, res) {
	fs.readFile('./scripts/joao/home/home.js', 'utf8', function(err, data) {
		res.send(data);
	});
});

router.post('/script', function(req, res) {
	var file = './scripts/joao/home/home.js';
	saveFile(file, req.body.body.script.content, function() {
		res.send("ok");
	});
})


module.exports = router;


//PRIVATE METHODS
function createRecursiveDir(dir, index) {
	if(!index) index = 0;
	if(index > dir.split("/").length) return;
	var path = "./" + dir.split("/").slice(1,index + 1).join("/");
	if (!fs.existsSync(path)){
	    fs.mkdirSync(path);
	    createRecursiveDir(dir, ++index);
	} else {
		createRecursiveDir(dir, ++index);
	}
};

function saveFile(file, content, callback) {
	createRecursiveDir(file);
	fs.writeFile(file, content, function() {
		callback();
	});
}