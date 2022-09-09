/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package watchful.edu.persistence.signature;

import java.util.List;

/**
 *
 * @author joao.schmitt
 */
public interface GenericDao<PK, T> {
    
    public void save(T t);
    
    public void save(List<T> t);
    
    public Object getSingle(Long id);
    
    public void delete(List<Long> ids);
    
    public void delete(Long id);
        
}
