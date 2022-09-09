package com.embedded.utils;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONException;
import org.json.JSONObject;

public final class JSONUtils {

	public static List<JSONObject> getComponents(JSONObject object) {
		List<JSONObject> components = new ArrayList<JSONObject>();
		try {
			for(int i = 0; i < object.getJSONObject("body").getJSONArray("components").length(); i++) {
				components.add(object.getJSONObject("body").getJSONArray("components").getJSONObject(i));
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return components;
	}
	
}
