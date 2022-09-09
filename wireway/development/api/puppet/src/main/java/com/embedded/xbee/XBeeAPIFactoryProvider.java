package com.embedded.xbee;

/**
 * This class return a instance of a implementer of XBeeAPI 
 * 
 * @author joao
 *
 */
public class XBeeAPIFactoryProvider {

	/**
	 * This method return some object that implements XBeeAPI
	 * 
	 * @param provider
	 * @return xBeeApi
	 */
	public static  <T extends XBeeAPI> T getProvider(Class<T> provider) {
		try {
			return (T) provider.newInstance();
		} catch (InstantiationException | IllegalAccessException e) {
			e.printStackTrace();
			System.exit(1);
			return null;
		}
	}
	
}
