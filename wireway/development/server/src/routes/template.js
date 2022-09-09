'use strict';

var express = require('express'),
	router = express.Router(),
	DAO;


router.get('/', function (req, res, next) {
	res.sendfile('./views/dashboard/manage.html')
});

router.get('/managetpl', function (req, res, next) {
	res.sendfile('./views/manageTpl.html')
});

router.get('/DashboardView', function (req, res, next) {
	DAO.WebTemplate.findByComponentType('DashboardView', function(err, entity) {
		res.json(entity);
	});
});

router.get('/All', function (req, res, next) {
	DAO.WebTemplate.findByComponentType(['Numeric','Digital', 'PWM', 'Analog',' Chart', 'Console'], function(err, entity) {
			res.json(entity);
	});
});

router.post('/webtpl', function(req, res) {
	DAO.WebTemplate.save(req.body, function(err, entity) {
		res.json(entity);
	});
});

router.get('/webtpl/:id', function(req, res) {
	DAO.WebTemplate.findById(req.params.id, function(err, data) {
		res.json(data);
	});
});

router.setDAO = function (db) {
	DAO = db;
};







var mockDashTemp = {
	componentType: "DashboardView",
	description: 'Main Panel - 3 columns',
	html: 	"<div class='container-fluid' id='dashboard'><div class='row'><div class='col-md-4' id='left'></div><div class='col-md-4' id='center'></div><div class='col-md-4' id='right'></div></div></div>",
};

var digitalTemplate = {
	componentType: 'Digital',
	description: 'I/O',
	html: "<hr /><div id='$id'><label id='$id-label' >$descriptionLabel</label>&nbsp&nbsp&nbsp<button class='btn btn-success' id='$id-btn'>OFF</button></div>",
	js: "jQuery('#$id-btn').click(function() {jQuery(this).html() === 'ON' ? jQuery(this).html('OFF') : jQuery(this).html('ON');wireway.sendComponent(wireway.getCmp('$id').getPacket());});wireway.getCmp('$id').getPacket = function() {var packet = {idName: this.webComponent.idName,value: this.el.children('button').html() == 'ON' ? 1 : 0,dataType: this.webComponent.dataType};return packet;};wireway.getCmp('$id').setPacket = function(data) {this.el.children('button').html(data.value == 0 ? 'OFF' : 'ON');}",
	css: "#$id-label { color: black; font-size: 16px; width: 60%; }#$id { padding: 10px; height: 70px; }#$id:hover { background-color: #EEEEEE; }#$id-btn { width: 30%; }",
	configHtml: '<div class="container-fluid"><div class="form-group"><div class="col-sm-4"><label>ID</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.idName"></div></div><div class="form-group"><div class="col-sm-4"><label>Description</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.description"></div></div><div class="form-group"><div class="col-sm-4"><label>Data Type</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.dataType"></div></div><div class="form-group"><div class="col-sm-4"><label>Component Type</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.componentType"></div></div><div class="form-group"><div class="col-sm-4"><label>Send When Change</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.sendWhenChange"></div></div><div class="form-group"><div class="col-sm-4"><label>Render TO</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.config.$renderTo"></div></div><div class="form-group"><div class="col-sm-4"><label>Label:</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.config.$descriptionLabel"></div></div><button class="btn btn-info" ng-click="createComponent()" data-dismiss="modal">Salvar</button></div>'
};

var pwmTemplate = {
	componentType: 'PWM',
	description: 'Pulse Width Modulation',
	html: "<hr /><div id='$id'><label id='$id-label' >$descriptionLabel</label>&nbsp&nbsp&nbsp&nbsp<label id='$id-label-value' >0</label><input id='$id-spinner' type='range' MIN='0' MAX='1024' step='1' value='0'></div>",
	js: "jQuery('#$id-spinner').on('change', function (e) {  wireway.sendComponent(wireway.getCmp('$id').getPacket());  jQuery('#$id-label-value')[0].innerHTML = wireway.getCmp('$id').getPacket().value; }); wireway.getCmp('$id').getPacket = function () {  var packet = {    idName: this.webComponent.idName,     value: jQuery('#$id-spinner').val(),    dataType: this.webComponent.dataType   };  return packet; }; wireway.getCmp('$id').setPacket = function (data) {     jQuery('#$id-spinner').val(parseInt(data.value));     jQuery('#$id-label-value')[0].innerHTML = data.value; }",
	css: "#$id-label { font-size: 16px; }#$id { padding: 10px; height: 70px; }#$id:hover { background-color: gray; }#$id-label-value { color: #EEEEEE; }",
	configHtml: '<div class="container-fluid"><div class="form-group"><div class="col-sm-4"><label>ID</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.idName"></div></div><div class="form-group"><div class="col-sm-4"><label>Description</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.description"></div></div><div class="form-group"><div class="col-sm-4"><label>Data Type</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.dataType"></div></div><div class="form-group"><div class="col-sm-4"><label>Component Type</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.componentType"></div></div><div class="form-group"><div class="col-sm-4"><label>Send When Change</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.sendWhenChange"></div></div><div class="form-group"><div class="col-sm-4"><label>Render TO</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.config.$renderTo"></div></div><div class="form-group"><div class="col-sm-4"><label>Label:</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.config.$descriptionLabel"></div></div><button class="btn btn-info" ng-click="createComponent()" data-dismiss="modal">Salvar</button></div>'
};

var labelTemplate = {
	componentType: 'Numeric',
	description: 'Numeric Label',
	html: "<hr /><div id='$id'><label id='$id-label' >$descriptionLabel</label>&nbsp&nbsp&nbsp&nbsp<label id='$id-label-value' >0</label></div>",
	js: "wireway.getCmp('$id').setPacket = function (data) {    jQuery('#$id-label-value')[0].innerHTML = data.value;  }",
	css: "#$id-label { font-size: 16px; }#$id { padding: 10px; height: 70px; }#$id:hover { background-color: gray; }#$id-label-value { color: #000000; }",
	configHtml: '<div class="container-fluid"><div class="form-group"><div class="col-sm-4"><label>ID</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.idName"></div></div><div class="form-group"><div class="col-sm-4"><label>Description</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.description"></div></div><div class="form-group"><div class="col-sm-4"><label>Data Type</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.dataType"></div></div><div class="form-group"><div class="col-sm-4"><label>Component Type</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.componentType"></div></div><div class="form-group"><div class="col-sm-4"><label>Send When Change</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.sendWhenChange"></div></div><div class="form-group"><div class="col-sm-4"><label>Render TO</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.config.$renderTo"></div></div><div class="form-group"><div class="col-sm-4"><label>Label:</label></div><div class="col-sm-8"><input type="text" class="form-control" ng-model="compConfig.config.$descriptionLabel"></div></div><button class="btn btn-info" ng-click="createComponent()" data-dismiss="modal">Salvar</button></div>'
};

router.get('/_1', function (req, res, next) {
	DAO.WebTemplate.save(mockDashTemp, function(err, entity) {
		console.info(entity.id);
		res.json(entity);
	});
});

router.get('/_2', function (req, res, next) {
	DAO.WebTemplate.save(digitalTemplate, function(err, entity) {
		console.info(entity.id);
		res.json(entity);
	});
});

router.get('/_3', function (req, res, next) {
	DAO.WebTemplate.save(pwmTemplate, function(err, entity) {
		console.info(entity.id);
		res.json(entity);
	});
});

router.get('/_4', function (req, res, next) {
	DAO.WebTemplate.save(labelTemplate, function(err, entity) {
		console.info(entity.id);
		res.json(entity);
	});
});

module.exports = router;