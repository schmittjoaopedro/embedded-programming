package com.embedded.exception;

public class EmbeddedException extends RuntimeException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public EmbeddedException() {
		super();
	}
	
	public EmbeddedException(String message) {
		super(message);
	}
	
	public EmbeddedException(Throwable throwable) {
		super(throwable);
	}
	
	public EmbeddedException(String message, Throwable throwable) {
		super(message, throwable);
	}
	
}
