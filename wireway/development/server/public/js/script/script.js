//ACE EDITOR PROGRAM
var editor = ace.edit("editor");
editor.setTheme("ace/theme/monokai");
editor.getSession().setMode("ace/mode/javascript");


//ANGULAR PROGRAM
var registerApp = angular.module('scriptApp', ['ngSanitize', 'ui.select']);


registerApp.filter('propsFilter', function() {
  return function(items, props) {
    var out = [];
    if (angular.isArray(items)) {
      items.forEach(function(item) {
        var itemMatches = false;
        var keys = Object.keys(props);
        for (var i = 0; i < keys.length; i++) {
          var prop = keys[i];
          var text = props[prop].toLowerCase();
          if (item[prop].toString().toLowerCase().indexOf(text) !== -1) {
            itemMatches = true;
            break;
          }
        }
        if (itemMatches) {
          out.push(item);
        }
      });
    } else {
      out = items;
    }
    return out;
  };
});


registerApp.controller('scriptCtrl', function ($scope, $http, $window, $compile) {

	//Usado pelo combo
	$scope.dashboard = {};

	$http.get('/dashboard/dashboards')
		.success(function(data) {
			$scope.dashboards = data;
		})
		.error(function(error) {
			alert(error);
		});

	$scope.loadTree = function() {
    jQuery('#documentTree').empty();
    $http({
      url: '/script/list', 
      method: "GET",
      params: { dashboardId: $scope.dashboard.selected.id }
   }).success(function(data) {
      if(data.success) {
          data.files.forEach(function(item) {
            console.info(item);
            addScript(item, true, $scope);
          });
          $scope.loadCurrent();
      }
   });
	};

  $scope.newScript = function() {
    var path = $scope.filepath;
    var name = $scope.filename;
    if(!!!path || !!!name) {
      alert('Path or name not seted!');
    } else {
      if(path.charAt(0) !== '/') path = '/' + path;
      if(path.charAt(path.length - 1) !== '/') path = path + '/';
      if(name.charAt(name.length - 3) +
         name.charAt(name.length - 2) +
         name.charAt(name.length - 1) !== '.js') name = name + '.js'; {
        var file = path + name;
        $http.get('/script/file', {
          params: {
            file: file, 
            dashboardId: $scope.dashboard.selected.id
          },
        }).success(function(data) {
          $scope.loadTree();
        }).error(function() {
          alert('Error to create file');
        });
      }
    }
  };

  $scope.loadFile = function (fileName) {
    $scope.currentFileName = fileName;
    $http({
      url: '/script/file', 
      method: "GET",
      params: { file: fileName, dashboardId: $scope.dashboard.selected.id }
   }).success(function(data) {
      editor.setValue(data.script);
   }).error(function(err) {
      alert(err);
   });
  };

  $scope.saveCurrent = function() {
    $http.post('/script/save', {
      file: $scope.currentFileName,
      dashboardId: $scope.dashboard.selected.id,
      script: editor.getValue()
    }).success(function() {
      alert('Save with success');
      $scope.loadTree();
    }).error(function() {
      alert('Error');
    });
  };


  $scope.useThisScript = function() {
    $http.post('/script/usethis', {
      file: $scope.currentFileName,
      dashboardId: $scope.dashboard.selected.id
    }).success(function() {
      alert('Save with success');
      $scope.loadTree();
    }).error(function() {
      alert('Error');
    });
  };

  $scope.loadCurrent = function() {
    if($scope.dashboard.selected.id)
      $http.get('/script/current/' + $scope.dashboard.selected.id).success(function(data) {
        jQuery('#document').find("a").attr('class', '');
        jQuery('#document').find("[fullpath='" + data.file + "']").attr('class', 'currentDocument');
      });
  };

});



//GLOBAL FUNCTIONS

function addScript(scriptFile, isNewDocument, $scope) {

  var path = scriptFile.split('/');
  path.splice(0, 1);
  var file = path.splice(path.length - 1, 1) [0];

  function processPathDocument(rootElement, fullPath, scriptName, index) {

    var children = $(rootElement).children('li');

    if (children.length > 0 && fullPath.length > index) {
      for (var i = 0; i < children.length; i++) {
        var labelChildName = $(children[i]).children('label').text();
        if (labelChildName === fullPath[index] && fullPath.length > index) {
          processPathDocument($(children[i]).children('ol')[0], fullPath, scriptName, ++index);
          return;
        }
      }
    }

    var li = $('<li>');
    if (index >= fullPath.length) {
      //ADD DOCUMENT
      var files = $(rootElement).children('a');
      var insert = true;
      files.each(function(idx, file) {
        if($(file).text() === scriptName) {
          insert = false;
        }
      });
      if(insert) {
        isNewDocument === true ?  li.attr('class', 'file-new') : li.attr('class', 'file');
        var a = $('<a>');
        a.text(scriptName);
        a.attr('href', '#');
        li.append(a);
        $(a).click(function(item) {
          $scope.loadFile(item.target.getAttribute('fullPath'));
          $('#documentTree').find('.selectDocument').each(function(idx, el) {
            $(el).attr('class', '');
          });
          $(this).attr('class', 'selectDocument');
        });
        $(rootElement).append(li);
        $(a).attr('fullPath', '/' + fullPath.join('/') + '/' + scriptName);
      }
    } else {
      //ADD NODE
      var label = $('<label>');
      label.attr('for', fullPath[index]);
      label.text(fullPath[index]);
      var check = $('<input>');
      check.attr('type', 'checkbox');
      check.attr('id', fullPath[index]);
      var ol = $('<ol>');
      li.append(label);
      li.append(check);
      li.append(ol);
      $(rootElement).append(li);
      check[0].checked = true
      processPathDocument(ol, fullPath, scriptName, ++index);
    }

  }

  processPathDocument($('#documentTree') [0], path, file, 0);

}

function expandTree() {
  var childrens = $('#documentTree').find('input');
  for(var i = 0; i < childrens.length; i++) {
    childrens[i].checked = true;
  }
}

function collpaseTree() {
  var childrens = $('#documentTree').find('input');
  for(var i = 0; i < childrens.length; i++) {
    childrens[i].checked = false;
  }
}