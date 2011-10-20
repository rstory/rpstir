/* ***** BEGIN LICENSE BLOCK *****
 * 
 * BBN Rule Editor/Engine for Address and AS Number PKI
 * Verison 1.0
 * 
 * COMMERCIAL COMPUTER SOFTWARE�RESTRICTED RIGHTS (JUNE 1987)
 * US government users are permitted restricted rights as
 * defined in the FAR.  
 *
 * This software is distributed on an "AS IS" basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 * Copyright (C) Raytheon BBN Technologies Corp. 2007.  All Rights Reserved.
 *
 * Contributor(s):  Charlie Gardiner
 *
 * ***** END LICENSE BLOCK ***** */
package certificate;
import orname.*;
import name.*;
import Algorithms.*;
// import serial_number.*;
import extensions.*;
import asn.*;
public class Validity extends AsnArray
    {
    public CertificateValidityDate notBefore = new CertificateValidityDate();
    public CertificateValidityDate notAfter = new CertificateValidityDate();
    public Validity()
        {
        _tag = AsnStatic.ASN_SEQUENCE;
        _type = (short)AsnStatic.ASN_SEQUENCE;
        _setup((AsnObj)null, notBefore, (short)0, (int)0x0);
        _setup(notBefore, notAfter, (short)0, (int)0x0);
        }
    public AsnObj _dup()
        {
        Validity objp = new Validity();
        _set_pointers(objp);
        return objp;
        }

    public Validity index(int index)
        {
        return (Validity)_index_op(index);
        }

    public Validity set(Validity frobj)
        {
        ((AsnObj)this).set(frobj);
	return this;
	}
    }