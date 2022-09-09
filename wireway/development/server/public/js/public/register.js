var registerApp = angular.module('registerApp', []);

registerApp.controller('RegisterCtrl', function ($scope, $http, $window) {

	$scope.saveSuccess = true;

	angular.extend($scope, {
        name: "",
        email: "",
        password: "",
        message: ""
    });

	$scope.valid = function() {
		var localMessage = $scope.runValidation();
		if(localMessage !== "OK") {
			$scope.message = localMessage;
			return false;
		} else {
			$scope.message = "";
			return true;
		}
		
	};

	$scope.runValidation = function() {
		if(!$scope.form) return 'Invalid register!'; 
		if(!$scope.form.name ) return 'User Name not defined!'; 
		if(!$scope.form.email ) return 'Email not defined!'; 
		if($scope.form.email) {
			var validEmailRegex = /^([\w-]+(?:\.[\w-]+)*)@((?:[\w-]+\.)*\w[\w-]{0,66})\.([a-z]{2,6}(?:\.[a-z]{2})?)$/i;
			if(!validEmailRegex.test($scope.form.email)) return 'Invalid Email!';
		}
		if(!$scope.form.password || !$scope.form.confirmPassword) return 'Password not defined!';
		if($scope.form.password !== $scope.form.confirmPassword) return 'Passwords must be equals!';
		if(!/^(?=.*[0-9])(?=.*[!@#$%^&*])[a-zA-Z0-9!@#$%^&*]{6,16}$/.test($scope.form.password)) return "Weak password! The password needs 5 or more characters have numbers, letters and special characters.";
		return "OK";
	}

	$scope.save = function() {
		if($scope.valid()) {
			var data = {
				name: $scope.form.name,
				email: $scope.form.email,
				password: $scope.form.password
			}
			$http.post('/register/user', data)
				.success(function() {
					$scope.saveSuccess = false;
				}).error(function(res) {
					$scope.message = res;
				});
		}
	};

});