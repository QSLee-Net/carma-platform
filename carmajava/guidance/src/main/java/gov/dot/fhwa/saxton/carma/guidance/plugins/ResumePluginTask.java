package gov.dot.fhwa.saxton.carma.guidance.plugins;

/**
 * Asynchronous task for invoking the Plugin's resume functionality
 */
public class ResumePluginTask implements Runnable {
    protected IPlugin plugin;
    protected TaskCompletionCallback callback;

    ResumePluginTask(IPlugin plugin, TaskCompletionCallback callback) {
        this.plugin = plugin;
        this.callback = callback;
    }

    @Override public void run() {
        plugin.onResume();
        callback.onComplete();
    }
}