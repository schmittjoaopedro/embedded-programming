var registerApp = angular.module('registerDashboardApp', []);


registerApp.controller('RegisterDashboardCtrl', function ($scope, $http, $window, $compile) {


	angular.extend($scope, {
        dashboardTemplate: [{
        	id: 0,
        	componentType: '',
        	html: '',
        	js: '',
        	css: '',
            description: ''
        }],
        componentTemplate: [{
        	id: 0,
        	componentType: '',
        	html: '',
        	js: '',
        	css: '',
            description: ''
        }],
        configHtml: '',
        compConfig: {},
        dashboard: {
            id: null,
            name: '',
            description: '',
            latitude: 0,
            longitude: 0,
            components: []
        }
    });

	$http.get('/template/All').success(function(data) {
		$scope.componentTemplate = data;
	});

    $http.get('/template/DashboardView').success(function(data) {
        $scope.dashboardTemplate = data;
    });

    $scope.instanceWebComponentModal = function(template) {
        var linkingFunction = $compile(template.configHtml);
        var elem = linkingFunction($scope);
        $scope.compConfig.webTemplate = template;
        $scope.compConfig.config = {};
        var compWebFormTemplate = document.getElementById("compWebFormTemplate");
        while (compWebFormTemplate.firstChild)
            compWebFormTemplate.removeChild(compWebFormTemplate.firstChild);
        compWebFormTemplate.appendChild(elem[0]);
    };

    $scope.defineDashboard = function(template) {
        var htmlDashboard = {
            webTemplate: template,
            config: {
                $renderTo: 'content'
            },
            idName: 'dashboardMain',
            componentType: 'DashboardView'
        };
        wireway.createComponent(htmlDashboard);
        wireway.setDashboard($scope.dashboard);
    };

    $scope.createComponent = function() {
        $scope.compConfig.config.$id = $scope.compConfig.idName;
        wireway.createComponent(JSON.parse(JSON.stringify($scope.compConfig)));
    }

    $scope.saveDashboard = function() {
        $http.post('/dashboard', wireway.getDashboard())
            .success(function(data) {
                alert("Saved with success!");
            })
            .error(function(err) {
                alert("Error: " + err);
            });
    };

    $http.get('/dashboard/dashboards').success(function(data) {
        $scope.dashboards = data;
    });

    $scope.clearDashboard = function() {
        wireway.clean();
    };

    $scope.loadDashboard = function(dashboard) {
        wireway.clean();
        $scope.dashboard = dashboard;
        wireway.setDashboard(dashboard);
        $http.get('/dashboard/dashboards/page/' + dashboard.id)
            .success(function(dashboard) {
                $http.get('/dashboard/dashboards/DashboardView/')
                    .success(function(dataMain) {
                        wireway.createComponent(dataMain);
                        $http.get('/dashboard/dashboards/All')
                        .success(function(dataItems) {
                            dataItems.forEach(function(item) {
                                wireway.createComponent(item);
                            });
                        })
                        .error(function(err) {
                            alert(err);
                        });
                    })
                    .error(function(err) {
                        alert(err);
                    });
            })
            .error(function(err) {
                alert(err);
            });
    };

});