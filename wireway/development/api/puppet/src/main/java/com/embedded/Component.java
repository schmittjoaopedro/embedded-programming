package com.embedded;


import java.util.ArrayList;
import java.util.List;

import org.json.JSONException;
import org.json.JSONObject;

import com.embedded.socket.CommunicationService;

public class Component {

	
	private Long id;
	
	private String idName;
	
	private String description;
	
	private String dataType;
	
	private String componentType;
	
	private Boolean sendWhenChange;
	
	private Object value;
	
	private Object lastValue;
	
	private List<ComponentEvent> listeners;
		
	
	public Long getId() {
		return id;
	}
	public void setId(Long id) {
		this.id = id;
	}
	public String getIdName() {
		return idName;
	}
	public void setIdName(String idName) {
		this.idName = idName;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getDataType() {
		return dataType;
	}
	public void setDataType(String dataType) {
		this.dataType = dataType;
	}
	public String getComponentType() {
		return componentType;
	}
	public void setComponentType(String componentType) {
		this.componentType = componentType;
	}
	public Boolean isSendWhenChange() {
		return sendWhenChange;
	}
	public void setSendWhenChange(Boolean sendWhenChange) {
		this.sendWhenChange = sendWhenChange;
	}
	public List<ComponentEvent> getListeners() {
		if(this.listeners == null) this.listeners = new ArrayList<ComponentEvent>();
		return listeners;
	}
	public void setListeners(List<ComponentEvent> listeners) {
		this.listeners = listeners;
	}
	public Object getValue() {
		return value;
	}
	public void setValue(Object value) {
		this.setLastValue(this.value);
		this.value = value;
		if(this.isSendWhenChange()) {
			if(this.getLastValue() == null || !this.getLastValue().equals(value)) {
				CommunicationService.getInstance().sendComponent(this);
			}
		} else {
			CommunicationService.getInstance().sendComponent(this);
		}
	}
	public void setRawValue(Object value) {
		this.value = value;
	}
	public void setAndNotify(Object value) {
		this.setLastValue(this.value);
		this.value = value;
		this.getListeners().forEach(item -> {
			item.data(value);
		});
	}
	public Object getLastValue() {
		return lastValue;
	}
	public void setLastValue(Object lastValue) {
		this.lastValue = lastValue;
	}
	public void on(ComponentEvent listener) {
		this.getListeners().add(listener);
	}
	
	public JSONObject getJsonObject() {
		JSONObject body = new JSONObject();
		try {
			body.put("id", this.getId());
			body.put("idName", this.getIdName());
			body.put("dataType", this.getDataType());
			body.put("componentType", this.getComponentType());
			body.put("value", this.getValue());
			body.put("lastValue", this.getLastValue());
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return body;
	}
	
}
