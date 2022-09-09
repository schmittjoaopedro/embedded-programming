

package watchful.edu.persistence.dao;

import java.lang.reflect.ParameterizedType;
import java.util.List;
import javax.ejb.EJB;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import watchful.edu.persistence.signature.GenericDao;

/**
 *
 * @author joao.schmitt
 * @param <PK>
 * @param <T>
 */
public abstract class GenericDaoImpl<PK, T> implements GenericDao<PK, T> {
    
    @PersistenceContext(unitName = "WatchfulPersistence")
    protected EntityManager entityManager;
    
    protected EntityManager getEntityManager() {
        return entityManager;
    }
    
    
    @Override
    public void save(Object t) {
        
        getEntityManager().persist(t);
    }
    
    @Override
    public void save(List<T> t) {
        for(Object item : t) {
            getEntityManager().persist(item);
        }
    }
    
    @Override
    public T getSingle(Long id) {
        return (T) getEntityManager().find(getTypeClass(), id);
    }
    
    @Override
    public void delete(List<Long> ids) {
        for(Long id : ids) {
            T record = getSingle(id);
            getEntityManager().remove(record);
        }
    }
    
    @Override
    public void delete(Long id) {
        T record = getSingle(id);
        getEntityManager().remove(record);
    }
    
    
    //Method for get type class extended this class
    private Class<?> getTypeClass() {
        Class<?> clazz = (Class<?>) ((ParameterizedType) this.getClass()
                .getGenericSuperclass()).getActualTypeArguments()[1];
        return clazz;
    }
}
