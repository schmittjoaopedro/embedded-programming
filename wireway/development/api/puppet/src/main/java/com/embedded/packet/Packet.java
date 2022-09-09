package com.embedded.packet;

import java.util.Arrays;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.embedded.Component;

public class Packet {

	private JSONObject header;
	private JSONObject body;
	
	private Packet(JSONObject header) {
		this.setHeader(header);
	}
	
	private Packet(JSONObject header, JSONObject body) {
		this.setHeader(header);
		this.setBody(body);
	}
	
	public JSONObject getHeader() {
		return header;
	}
	public void setHeader(JSONObject header) {
		this.header = header;
	}
	public JSONObject getBody() {
		return body;
	}
	public void setBody(JSONObject body) {
		this.body = body;
	}

	public static JSONObject newPacketHeader() {
		return new Packet(Header.getJsonObject()).getJsonObject();
	}
	
	public static JSONObject newPacket(Component component) {
		return Packet.newPacket(Arrays.asList(component));
	}
	public static JSONObject newPacket(List<Component> components) {
		try {
			JSONArray componentsArray = new JSONArray();
			components.forEach(item -> {
				componentsArray.put(item.getJsonObject());
			});
			JSONObject componentsObject = new JSONObject();
			componentsObject.put("components", componentsArray);
			return new Packet(Header.getJsonObject(), componentsObject).getJsonObject();
		} catch (JSONException e) {
			return Packet.newErroPacket(e);
		}
	}
	
	public static JSONObject newErroPacket(Exception ex) {
		try {
			JSONObject errorObject = new JSONObject();
			errorObject.put("message", ex.getMessage());
			errorObject.put("stacktrace", ex.getStackTrace());
			return new Packet(Header.getJsonObject(), errorObject).getJsonObject();
		} catch (Exception exInternal) {
			throw new RuntimeException(exInternal);
		}
		
	}
	
	public JSONObject getJsonObject() {
		JSONObject jsonObject = new JSONObject();
		try {
			jsonObject.put("header", this.getHeader());
			jsonObject.put("body", this.getBody());
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return jsonObject;
	}
	
}
