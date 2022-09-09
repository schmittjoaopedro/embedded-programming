var registerApp = angular.module('viewDashboardApp', []);


registerApp.controller('ViewDashboardCtrl', function ($scope, $http, $window, $compile) {

	$http.get('/dashboard/dashboards/DashboardView/')
		.success(function(dataMain) {
			wireway.createComponent(dataMain);
			$http.get('/dashboard/dashboards/All')
			.success(function(dataItems) {
				dataItems.forEach(function(item) {
					wireway.createComponent(item);
				});
				wireway.manager.start();
			})
			.error(function(err) {
				alert(err);
			});
		})
		.error(function(err) {
			alert(err);
		});

});