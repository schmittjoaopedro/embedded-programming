var registerApp = angular.module('registerTplApp', []);


registerApp.controller('RegisterTplCtrl', function ($scope, $http, $window, $sce) {


	angular.extend($scope, {
        tpl: [{
        	id: 0,
        	componentType: '',
        	html: '',
        	js: '',
        	css: '',
            description: '',
            configHtml: ''
        }]
    });

    $scope.find = function() {
        $http.get('/template/webtpl/' + $scope.tpl.id).
        success(function(data) {
            $scope.tpl = data;
        });
    };

    $scope.save = function() {
        $http.post('/template/webtpl', $scope.tpl).
        success(function(data) {
            $scope.tpl = data;
        });
    }

    $scope.tpl.id = 3;

});