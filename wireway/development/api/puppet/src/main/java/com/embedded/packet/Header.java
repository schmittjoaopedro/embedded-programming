package com.embedded.packet;

import org.json.JSONException;
import org.json.JSONObject;

public class Header {

	private static Long userId;
	private static String userName;
	private static String userPassword;
	private static Long dashboardId;
	private static final String type = "Middleware";

	private static Boolean isAuthenticated;
	private static String dashboardName;


	public static Long getUserId() {
		return userId;
	}
	public static void setUserId(Long userId) {
		Header.userId = userId;
	}
	public static String getUserName() {
		return userName;
	}
	public static void setUserName(String userName) {
		Header.userName = userName;
	}
	public static String getUserPassword() {
		return userPassword;
	}
	public static void setUserPassword(String userPassword) {
		Header.userPassword = userPassword;
	}
	public static Long getDashboardId() {
		return dashboardId;
	}
	public static void setDashboardId(Long dashboardId) {
		Header.dashboardId = dashboardId;
	}
	public static Boolean isAuthenticated() {
		return isAuthenticated;
	}
	public static void setIsAuthenticated(Boolean isAuthenticated) {
		Header.isAuthenticated = isAuthenticated;
	}
	public static String getDashboardName() {
		return dashboardName;
	}
	public static void setDashboardName(String dashboardName) {
		Header.dashboardName = dashboardName;
	}
	public static String getType() {
		return type;
	}


	public static JSONObject getJsonObject() {
		JSONObject header = new JSONObject();
		try {
			header.put("userId", Header.getUserId());
			header.put("userName", Header.getUserName());
			header.put("userPassword", Header.getUserPassword());
			header.put("dashboardId", Header.getDashboardId());
			header.put("type", Header.getType());
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return header;
	}
}
