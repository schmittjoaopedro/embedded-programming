/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package watchful.edu.resources;

import javax.ws.rs.GET;
import javax.ws.rs.Path;

/**
 *
 * @author joao.schmitt
 */
@Path("/home")
public class HomeResource {
    
    @GET
    public String helloWorld() {
        return "Hello Service";
    }
    
}
