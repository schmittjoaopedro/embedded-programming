if (!String.replaceAll)
	String.prototype.replaceAll = function(target, replacement) {
		return this.split(target).join(replacement);
	};


/**
 * ALL API is based in work with packet. Packet follow the structure below:
 *
 *
 *
 */
var wireway = (function() {


	var api = function() {
		this._version =  "0.0.1";
		this.components = [];
	};

	/**
	 * PRIVATE METHODS
	 */
	function processConfig(string, config) {
		if(string !== null) {
			if(!config ) console.info('Config not defined');
			var processedString = string;
			for(var c in config) {
				processedString = processedString.replaceAll(c, config[c]);
			}
			return processedString;
		}
	}
	function addStyleString(str) {
	    var node = document.createElement('style');
	    node.innerHTML = str;
	    document.body.appendChild(node);
	}


	api.prototype = {

		/**
		 *	CREATE SIGNATURE TO WEBCOMPONENT
		 */
		Component: (function() {

			function Component(identifier) {
				if(!identifier) throw Error("Need a identifier to create component");
				this.identifier = identifier;
			}

			Component.prototype.setWebComponent = function(component) {
				this.config = component.config;
				this.html = processConfig(component.webTemplate.html, this.config);
				this.js = processConfig(component.webTemplate.js, this.config);
				this.css = processConfig(component.webTemplate.css, this.config);
				this.renderTo = component.config.$renderTo;
				this.webComponent = component;
			}

			Component.prototype.getIdentificator = function() {
				return this.webComponent.idName;
			};

			Component.prototype.render = function() {
				if(!this.rendered) {
					this.rendered = true;
					$('#' + this.renderTo).append(this.html);
					this.el = $('#' + this.getIdentificator());
					if(this.js) eval(this.js);
					if(this.css) addStyleString(this.css);
				}
			};

			return Component;

		}())
	};


	/**
	 * API METHODS UTILITYS
	 */

	 //Add the component in memory, and care to do not add new components with same id
	api.prototype.addComponent = function (component) {
		if(!component.getIdentificator) {
			throw Error(component + " not is webComponent")
		}
		var contains = false;
		for(var comp in this.components) {
			if(this.components[comp].getIdentificator() === component.getIdentificator()) {
				contains = true;
			}
		}
		if(!contains) {
			this.components.push(component);
		}
	};

	//return component from api by id
	api.prototype.getCmp = function (componentName) {
		for(var comp in this.components) {
			if(this.components[comp].getIdentificator() === componentName) {
				return this.components[comp];
			}
		}
		return null;
	};

	//return all components
	api.prototype.getAllComponents = function() {
		return this.components;
	};

	//do render for view
	api.prototype.render = function() {
		for(var comp in this.components) {
			this.components[comp].render();
		}
	};

	//create componente and add to API
	api.prototype.createComponent = function(webComponent) {
		if(!!this.getCmp(webComponent.idName)) return;
		var comp = new this.Component(webComponent.idName);
		comp.setWebComponent(webComponent);
		this.addComponent(comp);
		this.render();
	};

	api.prototype.sendComponent = function(compPacket) {
		if(this.manager) {
			if(this.manager.sendComponent) {
				this.manager.sendComponent(compPacket);
			} else {
				throw Error('Managar not implement sendComponent');
			}
		}
	};

	api.prototype.processComponents = function(packet) {
		for(var cmp in packet.components) {
			wireway.getCmp(packet.components[cmp].idName).setPacket(packet.components[cmp]);
		}
	};

	api.prototype.setDashboard = function(dashboard) {
		this.dashboard = dashboard;
	};

	api.prototype.getDashboard = function(dashboard) {
		var dashboard = JSON.parse(JSON.stringify(this.dashboard));
		var components = [];
		wireway.components.forEach(function(item) {
			components.push(item.webComponent);
		});
		dashboard.components = components;
		return dashboard;
	};

	api.prototype.clean = function() {
		$('#content').empty();
		this.components = [];
	};

	api.prototype.removeComponent = function(idName) {
		$('#' + idName).remove();
		var index = -1;
		this.components.forEach(function(item, idx) {
			if(item.getIdentificator() === idName)
				index = idx;
		});
		if(index > -1)
			this.components.splice(index,1);
	};

	var apiInternal = new api();
	return apiInternal;

}());



/**
 * USAGE

wireway.createComponent(htmlDashboard);

wireway.createComponent(htmlDigitalComponent1);

wireway.createComponent(htmlDigitalComponent2);


var data = {
  dataType: "Number",
  idName: "digital1",
  value: 0
};
wireway.getCmp('digital1').setPacket(data);


wireway.getCmp('digital1').getPacket();

*/