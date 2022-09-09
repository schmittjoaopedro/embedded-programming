package wacthful.edu.persistence.commons;

import java.util.List;
import javax.ejb.EJB;

/**
 *
 * @author joao.schmitt
 */
public class JsonTransport {

    public Object data;
    public String error;
    public Boolean success;
    public Long count;
    
    
    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        if(data instanceof List) {
            List dataList = (List) data;
            this.setCount(Long.parseLong(String.valueOf(dataList.size())));
        } else {
            this.setCount(1L);
        }
        this.setSuccess(true);
        this.data = data;
    }

    public String getError() {
        return error;
    }

    public void setError(String error) {
        this.setSuccess(false);
        this.setCount(0L);
        this.error = error;
    }

    public Boolean isSuccess() {
        return success;
    }

    public void setSuccess(Boolean success) {
        this.success = success;
    }

    public Long getCount() {
        return count;
    }

    public void setCount(Long count) {
        this.count = count;
    }    
    
    
}
