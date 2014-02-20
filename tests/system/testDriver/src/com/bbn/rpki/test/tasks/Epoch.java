/*
 * Created on Feb 21, 2012
 */
package com.bbn.rpki.test.tasks;

import java.util.ArrayList;
import java.util.List;

import com.bbn.rpki.test.actions.EpochEvent;

/**
 * Contains all Epochs that are simultaneous
 *
 * @author tomlinso
 */
public class Epoch {
	private final List<EpochEvent> epochEvents = new ArrayList<EpochEvent>();

	//TODO is it ok for this to be an Integer?
	private Integer epochIndex;

	private long epochTime;

	private boolean epochTimeLocked;

	void addEpochEvent(EpochEvent epochEvent) {
		Epoch formerEpoch = epochEvent.getEpoch();
		if (formerEpoch != null) {
			formerEpoch.epochEvents.remove(epochEvent);
		}
		epochEvents.add(epochEvent);
		epochEvent.setEpoch(this);
	}

	/**
	 * @return the epochs
	 */
	public int getEpochEventCount() {
		return epochEvents.size();
	}

	/**
	 * @return the epochIndex
	 */
	public Integer getEpochIndex() {
		return epochIndex;
	}

	/**
	 * @param index
	 * @return the epoch at the specified index
	 */
	public EpochEvent getEpochEvent(int index) {
		return epochEvents.get(index);
	}

	/**
	 * @param epochIndex
	 *            the epochIndex to set
	 */
	public void setEpochIndex(Integer epochIndex) {
		this.epochIndex = epochIndex;
	}

	/**
	 * @return the epochs
	 */
	public List<EpochEvent> getEpochEvents() {
		return epochEvents;
	}

	/**
	 * @param child
	 * @return the index of the specified child
	 */
	public int indexOf(Object child) {
		return epochEvents.indexOf(child);
	}

	/**
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Epoch " + epochIndex;
	}

	/**
	 * This Epoch takes over the specified epoch. The specified epoch is left
	 * empty.
	 *
	 * @param epoch
	 */
	public void subsumeEpoch(Epoch epoch) {
		if (epoch != null && epoch != this) {
			List<EpochEvent> subsumedEpochEvents = epoch.getEpochEvents();
			for (int i = subsumedEpochEvents.size(); --i >= 0;) {
				EpochEvent epochEvent = subsumedEpochEvents.get(i);
				addEpochEvent(epochEvent);
			}
		}
	}

	/**Locks the epoch time
	 * @return the time at which this epoch should be executed
	 */
	public long getEpochTime() {
		epochTimeLocked = true;
		return epochTime;
	}

	/**
	 * @param epochTime
	 *            the time at which this epoch should be executed
	 */
	public void setEpochTime(long epochTime) {
		if (epochTimeLocked) {
			throw new RuntimeException(
					"Attempt to change epochTime when locked");
		}
		this.epochTime = epochTime;
	}
}