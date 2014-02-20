/*
 * Created on Jan 19, 2012
 */
package com.bbn.rpki.test.tasks;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import com.bbn.rpki.test.objects.Constants;
import com.bbn.rpki.test.objects.Util;
import com.bbn.rpki.test.tasks.ExtensionHandler.ExtensionFilter;

/**
 * UPloads multiple files to a publication point
 *
 * @author tomlinso
 */
public abstract class UploadFiles extends TaskFactory {

	protected class Task extends TaskFactory.Task {

		private final File directory;

		private final ExtensionFilter filter;

		/**
		 * @param taskName
		 */
		protected Task(String taskName, File directory, ExtensionFilter filter) {
			super(taskName);
			this.directory = directory;
			this.filter = filter;
		}

		@Override
		public void run() {
			List<File> filesToUpload = getFilesToUpload();
			if (filesToUpload.isEmpty()) {
				return;
			}
			List<String> cmd = new ArrayList<String>();
			cmd.add("cp");
			for (File file : filesToUpload) {
				cmd.add(file.getPath());
			}
			cmd.add(Constants.RSYNC_LOCAL);
			String title = UploadFiles.this.getClass().getSimpleName();
			Util.exec(title, false, new File(Constants.OBJECT_PATH), null, null, cmd);
		}

		public List<File> getFilesToUpload() {
			List<File> ret = new ArrayList<File>();
			for (File file : model.getWrittenFiles()) {
				if (file.getParentFile().equals(directory)
						&& (filter == null || filter.accept(file))) {
					ret.add(file);
				}
			}
			return ret;
		}

		/**
		 * @return the directory
		 */
		public File getDirectory() {
			return directory;
		}

		/**
		 * @see com.bbn.rpki.test.tasks.TaskFactory#getLogDetail()
		 */
		@Override
		protected final String getLogDetail() {
			String repository = model.getSCPFileNameArg(directory);
			return String.format("%d files to %s", getFilesToUpload().size(),
					repository);
		}
	}

	/**
	 * @param model
	 */
	public UploadFiles(Model model) {
		super(model);
	}
}