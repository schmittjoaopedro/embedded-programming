'use strict';

var express = require('express'),
	router = express.Router(),
	fs = require('fs'),
	mkdirp = require('mkdirp'),
	glob = require('glob'),
	DAO;





router.get('/', function (req, res, next) {
 	res.sendfile('./views/script.html');
});





router.get('/file', function (req, res, next) {
	var file = req.query.file;
	var dashboardId = req.query.dashboardId;

	if(file && dashboardId) {
		verifyOrCreateFile(dashboardId, file, res);
	} else {
		res.json({ success: false });
	}

});





router.get('/list', function(req, res, next) {
	var dashboardId = req.query.dashboardId;

	if(dashboardId) {
		var path = dashboardId;
		var root = "./scripts/" + dashboardId;
		glob(root + "/**/*.js", function(err, files) {
			for(var i = 0; i < files.length; i++) {
				files[i] = files[i].replace(root, "");
			}
			res.json({ success: true, files: files });
		});
	} else {
		res.json({ success: false });
	}
});





router.post('/save', function(req, res, next) {
	var data = req.body;

	if(!data.file && !data.dashboardId && !data.script) res.send(500);

	var path = 'scripts/' + data.dashboardId + data.file;
	fs.writeFile(path, data.script, function(err) {
	    if(err) {
	        return console.log(err);
	    }
	    verifyOrCreateFile(data.dashboardId, data.file, res);
	}); 

});




router.post('/usethis', function(req, res, next) {
	var data = req.body;

	if(!data.dashboardId && ! data.file) res.send(500);

	DAO.Dashboard.findById(data.dashboardId, function(err, dashboard) {
		if(err) res.send(500);
		if(dashboard) {
			dashboard.updateAttributes({
				currentScript: data.file
			}).success(function(dashboard) {
				res.send(200)
			}).error(function() {
				res.send(500);
			});			
		}
	});
});


router.get('/current/:dashboardId', function(req, res, next) {
	var dashboardId = req.params['dashboardId'];
	if(!dashboardId) res.send(500);
	DAO.Dashboard.findById(dashboardId, function(err, dashboard) {
		if(err) res.send(500);
		if(dashboard && dashboard.currentScript) {
			verifyOrCreateFile(dashboardId, dashboard.currentScript, res);
		} else {
			res.send({});
		}
	});
});



router.setDAO = function (db) {
	DAO = db;
};





function verifyOrCreateFile(dashboardId, filepath, res) {
	try {
		var file = './scripts/' + dashboardId + filepath;
		var path = file.split('/');
		var fileName = path[path.length - 1];
		path = './' + path.slice(0, path.length -1).join('/') + '/';

		mkdirp(path, function (err) {
			if(err) {
				res.json({ success: false });
			}
			fs.exists(file, function(exist) {
				if(exist) {
					fs.readFile(file, 'utf8', function (err, data) {
						if (err) {
							res.json({ success: false });
						}
						res.json({ success: true, script: data, file: filepath });
					});
				} else {
					fs.closeSync(fs.openSync(file, 'w'));
					res.json({ success: false });
				}
			});
		});
	} catch (err) {
		console.info(err);
		res.send(500);
	}
}




module.exports = router;