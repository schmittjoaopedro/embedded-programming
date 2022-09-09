/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package web.resources;

import arduino.watchful.communicate.SerialPortException;
import arduino.watchful.core.ControllerManager;
import arduino.watchful.core.DefinitionException;
import arduino.watchful.core.Digital;
import arduino.watchful.core.WireComponents;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.UriInfo;
import javax.ws.rs.Consumes;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;

/**
 * REST Web Service
 *
 * @author joao.schmitt
 */
@Path("main")
public class WatchfulResource {

    @Context
    private UriInfo context;
    
    public static WireComponents controller;
    private static Digital d1;

    public WatchfulResource() {
    }

    @GET
    @Produces("text/plain")
    public String getXml() {
        String r = "Adicionado com successo";
        
        try {
            WatchfulResource.controller = new WireComponents("COM17");
        } catch (SerialPortException ex) {
            r = ex.getMessage();
        }
        
        return r;
    }
    
    @GET
    @Path("begin")
    @Produces("text/plain")
    public String define() {
        String response = "Defined!";
        
        try {
            WatchfulResource.d1 = new Digital();
            WatchfulResource.d1.setPin(50);
            WatchfulResource.d1.setCommand("OUTPUT");
            WatchfulResource.controller.addControlled(d1);
            WatchfulResource.controller.define();
        } catch (Exception ex) {
            response = ex.getMessage();
        }
        return response;
    }

    @GET
    @Path("on")
    @Produces("text/plain")
    public String putXml(String content) {
        String response = "Is ON";
        WatchfulResource.d1.setValue("HIGH");
        try {
            WatchfulResource.controller.execute();
        } catch (DefinitionException ex) {
            response = ex.getMessage();
        } catch (SerialPortException ex) {
            response = ex.getMessage();
        }
        return response;
    }
    
    @GET
    @Path("off")
    @Produces("text/plain")
    public String powerOff(String content) {
        String response = "Is OFF";
        WatchfulResource.d1.setValue("LOW");
        try {
            WatchfulResource.controller.execute();
        } catch (DefinitionException ex) {
            response = ex.getMessage();
        } catch (SerialPortException ex) {
            response = ex.getMessage();
        }
        return response;
    }
    
    @GET
    @Path("teste")
    @Produces("text/plain")
    public String teste() {
        String response = "Success";
        
        try {
            controller = new WireComponents("COM17");
            Thread.sleep(1000);
            d1 = new Digital();
            d1.setPin(50);
            d1.setCommand("OUTPUT");
            controller.addControlled(d1);
            controller.define();
            Thread.sleep(2000);
            d1.setValue("HIGH");
            controller.execute();
            Thread.sleep(5000);
            d1.setValue("LOW");
            controller.execute();
        }catch(Exception er) {
            response = er.getMessage();
        }
        
        return response;
    }
    
    @GET
    @Path("users")
    @Produces("text/plain")
    public String getUser(){
        return "teste";
    }
}
