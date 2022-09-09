var registerApp = angular.module('viewDashboardApp', []);


registerApp.controller('ViewDashboardCtrl', function ($scope, $http, $window, $compile) {

	$http.get('/dashboard/dashboards').success(function(data) {
		$scope.dashboards = data;
	});

	$scope.selectDashboard = function(dashboard) {
		$window.location.href = '/dashboard/dashboards/page/' + dashboard.id;
	};

});