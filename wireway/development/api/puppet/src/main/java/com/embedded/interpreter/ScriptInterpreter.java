package com.embedded.interpreter;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

import com.embedded.Context;

public class ScriptInterpreter extends Thread {

	private ScriptEngine engine;
	private Boolean run = Boolean.TRUE;
	private ScriptEngineManager engineManager;
	private Boolean killed = Boolean.FALSE;
	
	public ScriptInterpreter() {
		engineManager = new ScriptEngineManager();
		engine = engineManager.getEngineByName("nashorn");
	}
	
	@Override
	public void run() {
		try {
			engine.eval("try { setup.call(_this); } catch(e) { print(e); }");
			engine.eval("try { while($interpreter.isRun()) { loop.call(_this); } } catch(e) { print(e); } $interpreter.finishKill()");
		} catch(Exception ex) {
			System.exit(1);
		}
	}
	
	public void uploadScript(String script, Context context) {
		try {
			engine.put("$interpreter", this);
			engine.put("_this", context);
			engine.eval(script);
		} catch (ScriptException e) {
			e.printStackTrace();
		}
	}
	
	public void stopScript() {
		try {
			this.setRun(false);
			while(!this.isKilled()) { Thread.sleep(5); };
			this.interrupt();
		} catch(InterruptedException ex) {
			ex.printStackTrace();
		}
	}
	
	public void finishKill() {
		this.setKilled(true);
	}

	
	public Boolean isRun() {
		return run;
	}
	public void setRun(Boolean run) {
		this.run = run;
	}

	public Boolean isKilled() {
		return killed;
	}
	public void setKilled(Boolean killed) {
		this.killed = killed;
	}
	
	
	
}
