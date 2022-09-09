package com.embedded.exception;

public class DashboardNotExistException extends EmbeddedException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public DashboardNotExistException() {
		super("Dashboard not created");
	}
	
	public DashboardNotExistException(String message) {
		super(message);
	}
	
	public DashboardNotExistException(Throwable throwable) {
		super(throwable);
	}
	
	public DashboardNotExistException(String message, Throwable throwable) {
		super(message, throwable);
	}
	
}
